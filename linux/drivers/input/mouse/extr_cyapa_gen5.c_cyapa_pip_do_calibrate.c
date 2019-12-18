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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cyapa {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PIP_SENSING_MODE_MUTUAL_CAP_FINE ; 
 int /*<<< orphan*/  PIP_SENSING_MODE_SELF_CAP ; 
 int cyapa_pip_calibrate_pwcs (struct cyapa*,int /*<<< orphan*/ ) ; 
 int cyapa_pip_resume_scanning (struct cyapa*) ; 
 int cyapa_pip_suspend_scanning (struct cyapa*) ; 
 struct cyapa* dev_get_drvdata (struct device*) ; 

ssize_t cyapa_pip_do_calibrate(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct cyapa *cyapa = dev_get_drvdata(dev);
	int error, calibrate_error;

	/* 1. Suspend Scanning*/
	error = cyapa_pip_suspend_scanning(cyapa);
	if (error)
		return error;

	/* 2. Do mutual capacitance fine calibrate. */
	calibrate_error = cyapa_pip_calibrate_pwcs(cyapa,
				PIP_SENSING_MODE_MUTUAL_CAP_FINE);
	if (calibrate_error)
		goto resume_scanning;

	/* 3. Do self capacitance calibrate. */
	calibrate_error = cyapa_pip_calibrate_pwcs(cyapa,
				PIP_SENSING_MODE_SELF_CAP);
	if (calibrate_error)
		goto resume_scanning;

resume_scanning:
	/* 4. Resume Scanning*/
	error = cyapa_pip_resume_scanning(cyapa);
	if (error || calibrate_error)
		return error ? error : calibrate_error;

	return count;
}