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
typedef  scalar_t__ u32 ;
struct platform_device {int dummy; } ;
struct db1x_pcmcia_sock {scalar_t__ virt_io; int /*<<< orphan*/  socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  db1x_pcmcia_free_irqs (struct db1x_pcmcia_sock*) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  kfree (struct db1x_pcmcia_sock*) ; 
 scalar_t__ mips_io_port_base ; 
 int /*<<< orphan*/  pcmcia_unregister_socket (int /*<<< orphan*/ *) ; 
 struct db1x_pcmcia_sock* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int db1x_pcmcia_socket_remove(struct platform_device *pdev)
{
	struct db1x_pcmcia_sock *sock = platform_get_drvdata(pdev);

	db1x_pcmcia_free_irqs(sock);
	pcmcia_unregister_socket(&sock->socket);
	iounmap((void *)(sock->virt_io + (u32)mips_io_port_base));
	kfree(sock);

	return 0;
}