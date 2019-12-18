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
typedef  scalar_t__ u32 ;
struct zfcp_latency_record {int /*<<< orphan*/  max; int /*<<< orphan*/  min; int /*<<< orphan*/  sum; } ;

/* Variables and functions */
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void zfcp_fsf_update_lat(struct zfcp_latency_record *lat_rec, u32 lat)
{
	lat_rec->sum += lat;
	lat_rec->min = min(lat_rec->min, lat);
	lat_rec->max = max(lat_rec->max, lat);
}