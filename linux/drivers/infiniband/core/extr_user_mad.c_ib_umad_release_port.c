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
struct ib_umad_port {struct ib_umad_device* umad_dev; } ;
struct ib_umad_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct ib_umad_port* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  ib_umad_dev_put (struct ib_umad_device*) ; 

__attribute__((used)) static void ib_umad_release_port(struct device *device)
{
	struct ib_umad_port *port = dev_get_drvdata(device);
	struct ib_umad_device *umad_dev = port->umad_dev;

	ib_umad_dev_put(umad_dev);
}