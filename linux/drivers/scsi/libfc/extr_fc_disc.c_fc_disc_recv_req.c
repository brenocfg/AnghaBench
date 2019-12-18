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
struct fc_disc {int /*<<< orphan*/  disc_mutex; } ;
struct fc_lport {struct fc_disc disc; } ;
struct fc_frame {int dummy; } ;

/* Variables and functions */
#define  ELS_RSCN 128 
 int /*<<< orphan*/  FC_DISC_DBG (struct fc_disc*,char*,int) ; 
 int /*<<< orphan*/  fc_disc_recv_rscn_req (struct fc_disc*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 int fc_frame_payload_op (struct fc_frame*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fc_disc_recv_req(struct fc_lport *lport, struct fc_frame *fp)
{
	u8 op;
	struct fc_disc *disc = &lport->disc;

	op = fc_frame_payload_op(fp);
	switch (op) {
	case ELS_RSCN:
		mutex_lock(&disc->disc_mutex);
		fc_disc_recv_rscn_req(disc, fp);
		mutex_unlock(&disc->disc_mutex);
		break;
	default:
		FC_DISC_DBG(disc, "Received an unsupported request, "
			    "the opcode is (%x)\n", op);
		fc_frame_free(fp);
		break;
	}
}