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
 int /*<<< orphan*/  b43_sdio_driver ; 
 int sdio_register_driver (int /*<<< orphan*/ *) ; 

int b43_sdio_init(void)
{
	return sdio_register_driver(&b43_sdio_driver);
}