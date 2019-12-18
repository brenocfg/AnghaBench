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
struct dvobj_priv {int /*<<< orphan*/  setbw_mutex; int /*<<< orphan*/  setch_mutex; int /*<<< orphan*/  h2c_fwcmd_mutex; int /*<<< orphan*/  hw_init_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct dvobj_priv*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void devobj_deinit(struct dvobj_priv *pdvobj)
{
	if (!pdvobj)
		return;

	mutex_destroy(&pdvobj->hw_init_mutex);
	mutex_destroy(&pdvobj->h2c_fwcmd_mutex);
	mutex_destroy(&pdvobj->setch_mutex);
	mutex_destroy(&pdvobj->setbw_mutex);

	kfree(pdvobj);
}