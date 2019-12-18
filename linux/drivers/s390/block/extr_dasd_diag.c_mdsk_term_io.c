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
struct TYPE_2__ {int /*<<< orphan*/  devno; } ;
struct dasd_diag_init_io {int /*<<< orphan*/  dev_nr; } ;
struct dasd_diag_private {TYPE_1__ dev_id; struct dasd_diag_init_io iib; } ;
struct dasd_device {struct dasd_diag_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  TERM_BIO ; 
 int dia250 (struct dasd_diag_init_io*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dasd_diag_init_io*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int
mdsk_term_io(struct dasd_device * device)
{
	struct dasd_diag_private *private = device->private;
	struct dasd_diag_init_io *iib = &private->iib;
	int rc;

	memset(iib, 0, sizeof (struct dasd_diag_init_io));
	iib->dev_nr = private->dev_id.devno;
	rc = dia250(iib, TERM_BIO);
	return rc;
}