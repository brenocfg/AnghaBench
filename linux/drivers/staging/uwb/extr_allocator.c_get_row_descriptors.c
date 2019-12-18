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
struct uwb_rsv_row_info {int free_rows; int* avail; } ;
struct uwb_rsv_alloc_info {unsigned char* bm; struct uwb_rsv_row_info ri; } ;

/* Variables and functions */
 int UWB_MAS_PER_ZONE ; 
 int UWB_NUM_ZONES ; 
 unsigned char UWB_RSV_MAS_NOT_AVAIL ; 

__attribute__((used)) static void get_row_descriptors(struct uwb_rsv_alloc_info *ai)
{
	unsigned char *bm = ai->bm;
	struct uwb_rsv_row_info *ri = &ai->ri;
	int col, mas;
  
	ri->free_rows = 16;
	for (mas = 0; mas < UWB_MAS_PER_ZONE; mas ++) {
		ri->avail[mas] = 1;
		for (col = 1; col < UWB_NUM_ZONES; col++) {
			if (bm[col * UWB_NUM_ZONES + mas] == UWB_RSV_MAS_NOT_AVAIL) {
				ri->free_rows--;
				ri->avail[mas]=0;
				break;
			}
		}
	}
}