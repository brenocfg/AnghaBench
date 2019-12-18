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
struct spi_message {int dummy; } ;
struct spi_controller {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int __spi_unmap_msg(struct spi_controller *ctlr,
				  struct spi_message *msg)
{
	return 0;
}