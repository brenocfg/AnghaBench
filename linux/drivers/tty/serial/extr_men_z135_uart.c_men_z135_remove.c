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
struct men_z135_port {scalar_t__ rxbuf; int /*<<< orphan*/  port; } ;
struct mcb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  line ; 
 struct men_z135_port* mcb_get_drvdata (struct mcb_device*) ; 
 int /*<<< orphan*/  men_z135_driver ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void men_z135_remove(struct mcb_device *mdev)
{
	struct men_z135_port *uart = mcb_get_drvdata(mdev);

	line--;
	uart_remove_one_port(&men_z135_driver, &uart->port);
	free_page((unsigned long) uart->rxbuf);
}