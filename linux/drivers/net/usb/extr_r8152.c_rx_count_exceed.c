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
struct r8152 {int /*<<< orphan*/  rx_count; } ;

/* Variables and functions */
 scalar_t__ RTL8152_MAX_RX ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool rx_count_exceed(struct r8152 *tp)
{
	return atomic_read(&tp->rx_count) > RTL8152_MAX_RX;
}