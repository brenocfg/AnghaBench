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

/* Variables and functions */
 int /*<<< orphan*/  SIO_CONFIG_KEY_EXIT ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_region (int,int) ; 

__attribute__((used)) static inline void sch311x_sio_exit(int sio_config_port)
{
	outb(SIO_CONFIG_KEY_EXIT, sio_config_port);
	release_region(sio_config_port, 2);
}