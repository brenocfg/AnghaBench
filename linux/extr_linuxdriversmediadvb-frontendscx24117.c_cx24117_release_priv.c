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
struct cx24117_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx24117_list_mutex ; 
 int /*<<< orphan*/  hybrid_tuner_release_state (struct cx24117_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cx24117_release_priv(struct cx24117_priv *priv)
{
	mutex_lock(&cx24117_list_mutex);
	if (priv != NULL)
		hybrid_tuner_release_state(priv);
	mutex_unlock(&cx24117_list_mutex);
}