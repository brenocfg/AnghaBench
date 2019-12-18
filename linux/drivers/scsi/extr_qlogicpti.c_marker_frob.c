#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int entry_cnt; int /*<<< orphan*/  entry_type; } ;
struct Marker_Entry {scalar_t__ rsvd; int /*<<< orphan*/  modifier; TYPE_1__ hdr; } ;
struct Command_Entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_MARKER ; 
 int /*<<< orphan*/  SYNC_ALL ; 
 int /*<<< orphan*/  memset (struct Marker_Entry*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void marker_frob(struct Command_Entry *cmd)
{
	struct Marker_Entry *marker = (struct Marker_Entry *) cmd;

	memset(marker, 0, sizeof(struct Marker_Entry));
	marker->hdr.entry_cnt = 1;
	marker->hdr.entry_type = ENTRY_MARKER;
	marker->modifier = SYNC_ALL;
	marker->rsvd = 0;
}