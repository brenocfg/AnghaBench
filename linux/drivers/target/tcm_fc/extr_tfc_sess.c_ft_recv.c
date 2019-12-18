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
typedef  int /*<<< orphan*/  u32 ;
struct ft_sess {int dummy; } ;
struct fc_lport {int dummy; } ;
struct fc_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TFC_SESS_DBG (struct fc_lport*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_frame_sid (struct fc_frame*) ; 
 int /*<<< orphan*/  ft_recv_req (struct ft_sess*,struct fc_frame*) ; 
 struct ft_sess* ft_sess_get (struct fc_lport*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ft_recv(struct fc_lport *lport, struct fc_frame *fp)
{
	struct ft_sess *sess;
	u32 sid = fc_frame_sid(fp);

	TFC_SESS_DBG(lport, "recv sid %x\n", sid);

	sess = ft_sess_get(lport, sid);
	if (!sess) {
		TFC_SESS_DBG(lport, "sid %x sess lookup failed\n", sid);
		/* TBD XXX - if FCP_CMND, send PRLO */
		fc_frame_free(fp);
		return;
	}
	ft_recv_req(sess, fp);	/* must do ft_sess_put() */
}