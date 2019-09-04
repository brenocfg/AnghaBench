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
struct opal_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_ADMINSP_UID ; 
 int /*<<< orphan*/  OPAL_ANYBODY_UID ; 
 int start_generic_opal_session (struct opal_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_anybodyASP_opal_session(struct opal_dev *dev, void *data)
{
	return start_generic_opal_session(dev, OPAL_ANYBODY_UID,
					  OPAL_ADMINSP_UID, NULL, 0);
}