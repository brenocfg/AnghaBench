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
struct mmphw_path_plat {int dummy; } ;
struct mmp_path {scalar_t__ plat_data; } ;

/* Variables and functions */

__attribute__((used)) static inline struct mmphw_path_plat *path_to_path_plat(struct mmp_path *path)
{
	return (struct mmphw_path_plat *)path->plat_data;
}