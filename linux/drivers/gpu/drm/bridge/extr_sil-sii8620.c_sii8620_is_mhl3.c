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
struct sii8620 {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ CM_MHL3 ; 

__attribute__((used)) static inline bool sii8620_is_mhl3(struct sii8620 *ctx)
{
	return ctx->mode >= CM_MHL3;
}