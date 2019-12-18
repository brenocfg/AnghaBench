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
struct msu_sink_private {struct msu_sink_private* sgts; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct msu_sink_private*) ; 

__attribute__((used)) static void msu_sink_unassign(void *data)
{
	struct msu_sink_private *priv = data;

	kfree(priv->sgts);
	kfree(priv);
}