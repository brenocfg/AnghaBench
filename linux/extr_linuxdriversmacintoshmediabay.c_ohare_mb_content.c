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
struct media_bay_info {int dummy; } ;

/* Variables and functions */
 int MB_IN32 (struct media_bay_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OHARE_MBCR ; 

__attribute__((used)) static u8
ohare_mb_content(struct media_bay_info *bay)
{
	return (MB_IN32(bay, OHARE_MBCR) >> 12) & 7;
}