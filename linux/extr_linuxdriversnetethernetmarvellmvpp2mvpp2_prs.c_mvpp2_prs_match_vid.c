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
struct mvpp2_prs_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mvpp2_prs_tcam_data_byte_set (struct mvpp2_prs_entry*,int,unsigned short,int) ; 

__attribute__((used)) static void mvpp2_prs_match_vid(struct mvpp2_prs_entry *pe, int offset,
				unsigned short vid)
{
	mvpp2_prs_tcam_data_byte_set(pe, offset + 0, (vid & 0xf00) >> 8, 0xf);
	mvpp2_prs_tcam_data_byte_set(pe, offset + 1, vid & 0xff, 0xff);
}