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
struct wf_ad7417_priv {int /*<<< orphan*/  ref; int /*<<< orphan*/ * sensors; int /*<<< orphan*/ * i2c; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct wf_ad7417_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wf_ad7417_release ; 
 int /*<<< orphan*/  wf_unregister_sensor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wf_ad7417_remove(struct i2c_client *client)
{
	struct wf_ad7417_priv *pv = dev_get_drvdata(&client->dev);
	int i;

	/* Mark client detached */
	pv->i2c = NULL;

	/* Release sensor */
	for (i = 0; i < 5; i++)
		wf_unregister_sensor(&pv->sensors[i]);

	kref_put(&pv->ref, wf_ad7417_release);

	return 0;
}