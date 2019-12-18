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
typedef  int /*<<< orphan*/  u32 ;
struct happy_meal {int dummy; } ;
typedef  int /*<<< orphan*/  hme32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u32 hme_read_desc32(struct happy_meal *hp, hme32 *p)
{
	return le32_to_cpup((__le32 *)p);
}