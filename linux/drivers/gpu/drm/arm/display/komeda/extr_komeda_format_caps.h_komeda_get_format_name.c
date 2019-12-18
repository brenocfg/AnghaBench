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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct drm_format_name_buf {int dummy; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 char* drm_get_format_name (int /*<<< orphan*/ ,struct drm_format_name_buf*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline const char *komeda_get_format_name(u32 fourcc, u64 modifier)
{
	struct drm_format_name_buf buf;
	static char name[64];

	snprintf(name, sizeof(name), "%s with modifier: 0x%llx.",
		 drm_get_format_name(fourcc, &buf), modifier);

	return name;
}