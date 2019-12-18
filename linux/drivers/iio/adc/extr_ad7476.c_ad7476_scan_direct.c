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
struct ad7476_state {scalar_t__ data; int /*<<< orphan*/  msg; int /*<<< orphan*/  spi; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int be16_to_cpup (int /*<<< orphan*/ *) ; 
 int spi_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad7476_scan_direct(struct ad7476_state *st)
{
	int ret;

	ret = spi_sync(st->spi, &st->msg);
	if (ret)
		return ret;

	return be16_to_cpup((__be16 *)st->data);
}