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
struct rt2x00_dev {int dummy; } ;
struct queue_entry {int dummy; } ;
typedef  enum rt2x00_dump_type { ____Placeholder_rt2x00_dump_type } rt2x00_dump_type ;

/* Variables and functions */

__attribute__((used)) static inline void rt2x00debug_dump_frame(struct rt2x00_dev *rt2x00dev,
					  enum rt2x00_dump_type type,
					  struct queue_entry *entry)
{
}