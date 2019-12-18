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
struct fw_device {int max_rec; } ;

/* Variables and functions */
 int min (int,int) ; 

__attribute__((used)) static inline int device_max_receive(struct fw_device *fw_device)
{
	/* see IEEE 1394-2008 table 8-8 */
	return min(2 << fw_device->max_rec, 4096);
}