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
struct diag204_x_info_blk_hdr {int /*<<< orphan*/  flags; } ;
struct diag204_info_blk_hdr {int /*<<< orphan*/  flags; } ;
typedef  enum diag204_format { ____Placeholder_diag204_format } diag204_format ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int DIAG204_INFO_SIMPLE ; 

__attribute__((used)) static inline __u8 info_blk_hdr__flags(enum diag204_format type, void *hdr)
{
	if (type == DIAG204_INFO_SIMPLE)
		return ((struct diag204_info_blk_hdr *)hdr)->flags;
	else /* DIAG204_INFO_EXT */
		return ((struct diag204_x_info_blk_hdr *)hdr)->flags;
}