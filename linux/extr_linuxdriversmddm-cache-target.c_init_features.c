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
struct cache_features {int metadata_version; int /*<<< orphan*/  io_mode; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_IO_WRITEBACK ; 
 int /*<<< orphan*/  CM_WRITE ; 

__attribute__((used)) static void init_features(struct cache_features *cf)
{
	cf->mode = CM_WRITE;
	cf->io_mode = CM_IO_WRITEBACK;
	cf->metadata_version = 1;
}