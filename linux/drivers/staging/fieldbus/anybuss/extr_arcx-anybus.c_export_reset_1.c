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
struct device {int dummy; } ;
struct controller_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  anybuss_reset (struct controller_priv*,int,int) ; 
 struct controller_priv* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static void export_reset_1(struct device *dev, bool assert)
{
	struct controller_priv *cd = dev_get_drvdata(dev);

	anybuss_reset(cd, 1, assert);
}