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
struct spi_transfer {scalar_t__ len; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SC18IS602_BUFSIZ ; 

__attribute__((used)) static int sc18is602_check_transfer(struct spi_device *spi,
				    struct spi_transfer *t, int tlen)
{
	if (t && t->len + tlen > SC18IS602_BUFSIZ)
		return -EINVAL;

	return 0;
}