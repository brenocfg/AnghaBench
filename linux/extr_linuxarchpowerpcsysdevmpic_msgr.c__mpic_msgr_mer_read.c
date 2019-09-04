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
struct mpic_msgr {int /*<<< orphan*/  mer; } ;

/* Variables and functions */
 int /*<<< orphan*/  in_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 _mpic_msgr_mer_read(struct mpic_msgr *msgr)
{
	return in_be32(msgr->mer);
}