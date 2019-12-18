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
struct txbd8 {int dummy; } ;

/* Variables and functions */
 struct txbd8* skip_txbd (struct txbd8*,int,struct txbd8*,int) ; 

__attribute__((used)) static inline struct txbd8 *next_txbd(struct txbd8 *bdp, struct txbd8 *base,
				      int ring_size)
{
	return skip_txbd(bdp, 1, base, ring_size);
}