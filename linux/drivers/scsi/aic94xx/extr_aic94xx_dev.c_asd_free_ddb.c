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
struct asd_ha_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_DDB (int,struct asd_ha_struct*) ; 
 int /*<<< orphan*/  DDB_TYPE ; 
 int /*<<< orphan*/  DDB_TYPE_UNUSED ; 
 int /*<<< orphan*/  asd_ddbsite_write_byte (struct asd_ha_struct*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asd_free_ddb(struct asd_ha_struct *asd_ha, int ddb)
{
	if (!ddb || ddb >= 0xFFFF)
		return;
	asd_ddbsite_write_byte(asd_ha, ddb, DDB_TYPE, DDB_TYPE_UNUSED);
	CLEAR_DDB(ddb, asd_ha);
}