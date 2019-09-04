#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ io_mode; } ;
struct cache {TYPE_1__ features; } ;

/* Variables and functions */
 scalar_t__ CM_IO_WRITETHROUGH ; 

__attribute__((used)) static bool writethrough_mode(struct cache *cache)
{
	return cache->features.io_mode == CM_IO_WRITETHROUGH;
}