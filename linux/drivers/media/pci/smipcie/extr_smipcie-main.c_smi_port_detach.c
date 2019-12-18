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
struct smi_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  smi_dvb_exit (struct smi_port*) ; 
 int /*<<< orphan*/  smi_fe_exit (struct smi_port*) ; 
 int /*<<< orphan*/  smi_port_exit (struct smi_port*) ; 

__attribute__((used)) static void smi_port_detach(struct smi_port *port)
{
	smi_fe_exit(port);
	smi_dvb_exit(port);
	smi_port_exit(port);
}