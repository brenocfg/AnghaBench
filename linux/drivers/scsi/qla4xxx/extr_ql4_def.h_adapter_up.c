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
struct scsi_qla_host {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LINK_UP ; 
 int /*<<< orphan*/  AF_LOOPBACK ; 
 int /*<<< orphan*/  AF_ONLINE ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int adapter_up(struct scsi_qla_host *ha)
{
	return (test_bit(AF_ONLINE, &ha->flags) != 0) &&
	       (test_bit(AF_LINK_UP, &ha->flags) != 0) &&
	       (!test_bit(AF_LOOPBACK, &ha->flags));
}