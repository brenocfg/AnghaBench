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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 scalar_t__ EXT_VIDEO_CAP_BLOCK_Y420CMDB ; 
 scalar_t__ USE_EXTENDED_TAG ; 
 scalar_t__ cea_db_extended_tag (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cea_db_payload_len (int /*<<< orphan*/  const*) ; 
 scalar_t__ cea_db_tag (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static bool cea_db_is_y420cmdb(const u8 *db)
{
	if (cea_db_tag(db) != USE_EXTENDED_TAG)
		return false;

	if (!cea_db_payload_len(db))
		return false;

	if (cea_db_extended_tag(db) != EXT_VIDEO_CAP_BLOCK_Y420CMDB)
		return false;

	return true;
}