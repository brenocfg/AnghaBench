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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int,scalar_t__,int) ; 
 int pcd_buf ; 
 int pcd_bufblk ; 
 scalar_t__ pcd_buffer ; 
 scalar_t__ pcd_count ; 
 int pcd_sector ; 

__attribute__((used)) static void pcd_transfer(void)
{

	while (pcd_count && (pcd_sector / 4 == pcd_bufblk)) {
		int o = (pcd_sector % 4) * 512;
		memcpy(pcd_buf, pcd_buffer + o, 512);
		pcd_count--;
		pcd_buf += 512;
		pcd_sector++;
	}
}