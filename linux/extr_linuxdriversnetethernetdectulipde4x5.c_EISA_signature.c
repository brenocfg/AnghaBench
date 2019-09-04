#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int driver_data; } ;
struct eisa_device {TYPE_1__ id; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * de4x5_signatures ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 struct eisa_device* to_eisa_device (struct device*) ; 

__attribute__((used)) static int
EISA_signature(char *name, struct device *device)
{
    int i, status = 0, siglen = ARRAY_SIZE(de4x5_signatures);
    struct eisa_device *edev;

    *name = '\0';
    edev = to_eisa_device (device);
    i = edev->id.driver_data;

    if (i >= 0 && i < siglen) {
	    strcpy (name, de4x5_signatures[i]);
	    status = 1;
    }

    return status;                         /* return the device name string */
}