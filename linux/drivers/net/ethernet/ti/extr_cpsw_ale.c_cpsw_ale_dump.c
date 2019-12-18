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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int ale_entries; } ;
struct cpsw_ale {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_ENTRY_WORDS ; 
 int /*<<< orphan*/  cpsw_ale_read (struct cpsw_ale*,int,int /*<<< orphan*/ *) ; 

void cpsw_ale_dump(struct cpsw_ale *ale, u32 *data)
{
	int i;

	for (i = 0; i < ale->params.ale_entries; i++) {
		cpsw_ale_read(ale, i, data);
		data += ALE_ENTRY_WORDS;
	}
}