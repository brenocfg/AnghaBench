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
typedef  int /*<<< orphan*/  u8 ;
struct hdcp_srm_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_hdcp_parse_hdcp1_srm (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  drm_hdcp_parse_hdcp2_srm (int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ is_srm_version_hdcp1 (int /*<<< orphan*/  const*) ; 
 scalar_t__ is_srm_version_hdcp2 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void drm_hdcp_srm_update(const u8 *buf, size_t count)
{
	if (count < sizeof(struct hdcp_srm_header))
		return;

	if (is_srm_version_hdcp1(buf))
		drm_hdcp_parse_hdcp1_srm(buf, count);
	else if (is_srm_version_hdcp2(buf))
		drm_hdcp_parse_hdcp2_srm(buf, count);
}