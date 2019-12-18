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
struct tb {scalar_t__ privdata; } ;

/* Variables and functions */

__attribute__((used)) static inline void *tb_priv(struct tb *tb)
{
	return (void *)tb->privdata;
}