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
typedef  scalar_t__ u64 ;
struct opal_scom_map {int /*<<< orphan*/  chip; scalar_t__ addr; } ;
typedef  struct opal_scom_map* scom_map_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 scalar_t__ opal_scom_unmangle (scalar_t__) ; 
 int opal_xscom_err_xlate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opal_xscom_write (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int opal_scom_write(scom_map_t map, u64 reg, u64 value)
{
	struct opal_scom_map *m = map;
	int64_t rc;

	reg = opal_scom_unmangle(m->addr + reg);
	rc = opal_xscom_write(m->chip, reg, value);
	return opal_xscom_err_xlate(rc);
}