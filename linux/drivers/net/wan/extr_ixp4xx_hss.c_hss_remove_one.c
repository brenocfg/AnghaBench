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
struct port {int /*<<< orphan*/  npe; int /*<<< orphan*/  netdev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct port*) ; 
 int /*<<< orphan*/  npe_release (int /*<<< orphan*/ ) ; 
 struct port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_hdlc_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hss_remove_one(struct platform_device *pdev)
{
	struct port *port = platform_get_drvdata(pdev);

	unregister_hdlc_device(port->netdev);
	free_netdev(port->netdev);
	npe_release(port->npe);
	kfree(port);
	return 0;
}