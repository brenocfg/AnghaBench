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
struct cmd_priv {int /*<<< orphan*/  sctx_mutex; int /*<<< orphan*/  rsp_allocated_buf; int /*<<< orphan*/  cmd_allocated_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void _rtw_free_cmd_priv(struct	cmd_priv *pcmdpriv)
{
	if (pcmdpriv) {
		kfree(pcmdpriv->cmd_allocated_buf);

		kfree(pcmdpriv->rsp_allocated_buf);

		mutex_destroy(&pcmdpriv->sctx_mutex);
	}
}