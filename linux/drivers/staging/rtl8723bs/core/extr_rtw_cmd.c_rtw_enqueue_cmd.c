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
struct cmd_priv {int /*<<< orphan*/  cmd_queue_comp; int /*<<< orphan*/  cmd_queue; struct adapter* padapter; } ;
struct cmd_obj {struct adapter* padapter; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int _FAIL ; 
 int _SUCCESS ; 
 int _rtw_enqueue_cmd (int /*<<< orphan*/ *,struct cmd_obj*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int rtw_cmd_filter (struct cmd_priv*,struct cmd_obj*) ; 
 int /*<<< orphan*/  rtw_free_cmd_obj (struct cmd_obj*) ; 

int rtw_enqueue_cmd(struct cmd_priv *pcmdpriv, struct cmd_obj *cmd_obj)
{
	int res = _FAIL;
	struct adapter *padapter = pcmdpriv->padapter;

	if (cmd_obj == NULL) {
		goto exit;
	}

	cmd_obj->padapter = padapter;

	res = rtw_cmd_filter(pcmdpriv, cmd_obj);
	if (_FAIL == res) {
		rtw_free_cmd_obj(cmd_obj);
		goto exit;
	}

	res = _rtw_enqueue_cmd(&pcmdpriv->cmd_queue, cmd_obj);

	if (res == _SUCCESS)
		complete(&pcmdpriv->cmd_queue_comp);

exit:
	return res;
}