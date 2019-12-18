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
struct scaler_format {scalar_t__ drm_fmt; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct scaler_format const*) ; 
 struct scaler_format const* scaler_formats ; 

__attribute__((used)) static const struct scaler_format *scaler_get_format(u32 drm_fmt)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(scaler_formats); i++)
		if (scaler_formats[i].drm_fmt == drm_fmt)
			return &scaler_formats[i];

	return NULL;
}