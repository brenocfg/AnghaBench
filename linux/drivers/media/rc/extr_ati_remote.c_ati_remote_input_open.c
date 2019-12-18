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
struct input_dev {int dummy; } ;
struct ati_remote {int dummy; } ;

/* Variables and functions */
 int ati_remote_open (struct ati_remote*) ; 
 struct ati_remote* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int ati_remote_input_open(struct input_dev *inputdev)
{
	struct ati_remote *ati_remote = input_get_drvdata(inputdev);
	return ati_remote_open(ati_remote);
}