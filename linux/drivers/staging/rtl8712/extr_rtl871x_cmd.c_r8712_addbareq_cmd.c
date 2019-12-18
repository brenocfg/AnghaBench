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
typedef  int /*<<< orphan*/  u8 ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int dummy; } ;
struct addBaReq_parm {int /*<<< orphan*/  tid; } ;
struct _adapter {struct cmd_priv cmdpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_CMD_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  _AddBAReq ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct addBaReq_parm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cmd_obj*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_enqueue_cmd_ex (struct cmd_priv*,struct cmd_obj*) ; 

void r8712_addbareq_cmd(struct _adapter *padapter, u8 tid)
{
	struct cmd_priv		*pcmdpriv = &padapter->cmdpriv;
	struct cmd_obj		*ph2c;
	struct addBaReq_parm	*paddbareq_parm;

	ph2c = kmalloc(sizeof(*ph2c), GFP_ATOMIC);
	if (!ph2c)
		return;
	paddbareq_parm = kmalloc(sizeof(*paddbareq_parm), GFP_ATOMIC);
	if (!paddbareq_parm) {
		kfree(ph2c);
		return;
	}
	paddbareq_parm->tid = tid;
	init_h2fwcmd_w_parm_no_rsp(ph2c, paddbareq_parm,
				   GEN_CMD_CODE(_AddBAReq));
	r8712_enqueue_cmd_ex(pcmdpriv, ph2c);
}