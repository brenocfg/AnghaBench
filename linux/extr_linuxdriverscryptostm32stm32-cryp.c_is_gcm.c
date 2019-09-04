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
struct stm32_cryp {int flags; } ;

/* Variables and functions */
 int FLG_GCM ; 

__attribute__((used)) static inline bool is_gcm(struct stm32_cryp *cryp)
{
	return cryp->flags & FLG_GCM;
}