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
typedef  int u8 ;

/* Variables and functions */
 unsigned int HDMI_FORUM_IEEE_OUI ; 
 scalar_t__ VENDOR_BLOCK ; 
 int cea_db_payload_len (int const*) ; 
 scalar_t__ cea_db_tag (int const*) ; 

__attribute__((used)) static bool cea_db_is_hdmi_forum_vsdb(const u8 *db)
{
	unsigned int oui;

	if (cea_db_tag(db) != VENDOR_BLOCK)
		return false;

	if (cea_db_payload_len(db) < 7)
		return false;

	oui = db[3] << 16 | db[2] << 8 | db[1];

	return oui == HDMI_FORUM_IEEE_OUI;
}