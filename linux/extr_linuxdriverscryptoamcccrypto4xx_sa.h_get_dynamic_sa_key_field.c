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
struct dynamic_sa_ctl {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */

__attribute__((used)) static inline __le32 *get_dynamic_sa_key_field(struct dynamic_sa_ctl *cts)
{
	return (__le32 *) ((unsigned long)cts + sizeof(struct dynamic_sa_ctl));
}