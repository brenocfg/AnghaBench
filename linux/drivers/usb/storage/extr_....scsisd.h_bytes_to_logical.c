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
struct scsi_device {int /*<<< orphan*/  sector_size; } ;
typedef  unsigned int sector_t ;

/* Variables and functions */
 unsigned int ilog2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline sector_t bytes_to_logical(struct scsi_device *sdev, unsigned int bytes)
{
	return bytes >> ilog2(sdev->sector_size);
}