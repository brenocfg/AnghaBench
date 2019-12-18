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
struct profi_priv {int /*<<< orphan*/  fbdev; } ;
struct anybuss_client {int dummy; } ;

/* Variables and functions */
 struct profi_priv* anybuss_get_drvdata (struct anybuss_client*) ; 
 int /*<<< orphan*/  fieldbus_dev_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int profinet_remove(struct anybuss_client *client)
{
	struct profi_priv *priv = anybuss_get_drvdata(client);

	fieldbus_dev_unregister(&priv->fbdev);
	return 0;
}