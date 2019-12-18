#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct tuner_types {char* fw_name; int tuner_type; int /*<<< orphan*/  tuner_name; } ;
struct dst_types {size_t offset; char* device_id; int dst_type; int tuner_type; int /*<<< orphan*/  dst_feature; int /*<<< orphan*/  type_flags; } ;
struct dst_state {int tuner_type; int* rxbuffer; int dst_type; int /*<<< orphan*/  type_flags; int /*<<< orphan*/  fw_name; int /*<<< orphan*/  dst_hw_cap; } ;

/* Variables and functions */
 int ACK ; 
 int ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  DEVICE_INIT ; 
 int /*<<< orphan*/  DST_TYPE_HAS_SYMDIV ; 
#define  DST_TYPE_IS_SAT 128 
 int /*<<< orphan*/  FIXED_COMM ; 
 int /*<<< orphan*/  GET_ACK ; 
 int TUNER_TYPE_MB86A15 ; 
 int TUNER_TYPE_MULTI ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 scalar_t__ dst_check_mb86a15 (struct dst_state*) ; 
 int /*<<< orphan*/  dst_check_stv0299 (struct dst_state*) ; 
 int dst_check_sum (int*,int) ; 
 scalar_t__ dst_pio_disable (struct dst_state*) ; 
 void* dst_tlist ; 
 int /*<<< orphan*/  dst_type_flags_print (struct dst_state*) ; 
 int /*<<< orphan*/  dst_type_print (struct dst_state*,int) ; 
 int /*<<< orphan*/  dst_wait_dst_ready (struct dst_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 scalar_t__ read_dst (struct dst_state*,int*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 void* tuner_list ; 
 scalar_t__ write_dst (struct dst_state*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dst_get_device_id(struct dst_state *state)
{
	u8 reply;

	int i, j;
	struct dst_types *p_dst_type = NULL;
	struct tuner_types *p_tuner_list = NULL;

	u8 use_dst_type = 0;
	u32 use_type_flags = 0;

	static u8 device_type[8] = {0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff};

	state->tuner_type = 0;
	device_type[7] = dst_check_sum(device_type, 7);

	if (write_dst(state, device_type, FIXED_COMM))
		return -1;		/*	Write failed		*/
	if ((dst_pio_disable(state)) < 0)
		return -1;
	if (read_dst(state, &reply, GET_ACK))
		return -1;		/*	Read failure		*/
	if (reply != ACK) {
		dprintk(2, "Write not Acknowledged! [Reply=0x%02x]\n", reply);
		return -1;		/*	Unack'd write		*/
	}
	if (!dst_wait_dst_ready(state, DEVICE_INIT))
		return -1;		/*	DST not ready yet	*/
	if (read_dst(state, state->rxbuffer, FIXED_COMM))
		return -1;

	dst_pio_disable(state);
	if (state->rxbuffer[7] != dst_check_sum(state->rxbuffer, 7)) {
		dprintk(2, "Checksum failure!\n");
		return -1;		/*	Checksum failure	*/
	}
	state->rxbuffer[7] = '\0';

	for (i = 0, p_dst_type = dst_tlist; i < ARRAY_SIZE(dst_tlist); i++, p_dst_type++) {
		if (!strncmp (&state->rxbuffer[p_dst_type->offset], p_dst_type->device_id, strlen (p_dst_type->device_id))) {
			use_type_flags = p_dst_type->type_flags;
			use_dst_type = p_dst_type->dst_type;

			/*	Card capabilities	*/
			state->dst_hw_cap = p_dst_type->dst_feature;
			pr_err("Recognise [%s]\n", p_dst_type->device_id);
			strscpy(state->fw_name, p_dst_type->device_id,
			        sizeof(state->fw_name));
			/*	Multiple tuners		*/
			if (p_dst_type->tuner_type & TUNER_TYPE_MULTI) {
				switch (use_dst_type) {
				case DST_TYPE_IS_SAT:
					/*	STV0299 check	*/
					if (dst_check_stv0299(state) < 0) {
						pr_err("Unsupported\n");
						state->tuner_type = TUNER_TYPE_MB86A15;
					}
					break;
				default:
					break;
				}
				if (dst_check_mb86a15(state) < 0)
					pr_err("Unsupported\n");
			/*	Single tuner		*/
			} else {
				state->tuner_type = p_dst_type->tuner_type;
			}
			for (j = 0, p_tuner_list = tuner_list; j < ARRAY_SIZE(tuner_list); j++, p_tuner_list++) {
				if (!(strncmp(p_dst_type->device_id, p_tuner_list->fw_name, 7)) &&
					p_tuner_list->tuner_type == state->tuner_type) {
					pr_err("[%s] has a [%s]\n",
						p_dst_type->device_id, p_tuner_list->tuner_name);
				}
			}
			break;
		}
	}

	if (i >= ARRAY_SIZE(dst_tlist)) {
		pr_err("Unable to recognize %s or %s\n", &state->rxbuffer[0], &state->rxbuffer[1]);
		pr_err("please email linux-dvb@linuxtv.org with this type in");
		use_dst_type = DST_TYPE_IS_SAT;
		use_type_flags = DST_TYPE_HAS_SYMDIV;
	}
	dst_type_print(state, use_dst_type);
	state->type_flags = use_type_flags;
	state->dst_type = use_dst_type;
	dst_type_flags_print(state);

	return 0;
}