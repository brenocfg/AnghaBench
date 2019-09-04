#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  mbx_if_lock; int /*<<< orphan*/  fw_is_running; } ;
struct TYPE_4__ {TYPE_1__ risc; } ;
struct dib9000_state {TYPE_2__ platform; } ;

/* Variables and functions */
 int MBX_MAX_WORDS ; 
 int /*<<< orphan*/  dib9000_read16_noinc_attr (struct dib9000_state*,int,int*,int,int) ; 
 int dib9000_read_word_attr (struct dib9000_state*,int,int) ; 
 int /*<<< orphan*/  dib9000_write_word_attr (struct dib9000_state*,int,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 dib9000_mbx_read(struct dib9000_state *state, u16 * data, u8 risc_id, u16 attr)
{
#ifdef DUMP_MSG
	u16 *d = data;
#endif

	u16 tmp, i;
	u8 size;
	u8 mc_base;

	if (!state->platform.risc.fw_is_running)
		return 0;

	if (mutex_lock_interruptible(&state->platform.risc.mbx_if_lock) < 0) {
		dprintk("could not get the lock\n");
		return 0;
	}
	if (risc_id == 1)
		mc_base = 16;
	else
		mc_base = 0;

	/* Length and type in the first word */
	*data = dib9000_read_word_attr(state, 1029 + mc_base, attr);

	size = *data & 0xff;
	if (size <= MBX_MAX_WORDS) {
		data++;
		size--;		/* Initial word already read */

		dib9000_read16_noinc_attr(state, 1029 + mc_base, (u8 *) data, size * 2, attr);

		/* to word conversion */
		for (i = 0; i < size; i++) {
			tmp = *data;
			*data = (tmp >> 8) | (tmp << 8);
			data++;
		}

#ifdef DUMP_MSG
		dprintk("<--\n");
		for (i = 0; i < size + 1; i++)
			dprintk("%04x\n", d[i]);
		dprintk("\n");
#endif
	} else {
		dprintk("MBX: message is too big for message cache (%d), flushing message\n", size);
		size--;		/* Initial word already read */
		while (size--)
			dib9000_read16_noinc_attr(state, 1029 + mc_base, (u8 *) data, 2, attr);
	}
	/* Update register nb_mes_in_TX */
	dib9000_write_word_attr(state, 1028 + mc_base, 1 << 14, attr);

	mutex_unlock(&state->platform.risc.mbx_if_lock);

	return size + 1;
}