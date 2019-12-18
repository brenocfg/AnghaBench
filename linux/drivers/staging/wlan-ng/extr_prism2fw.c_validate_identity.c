#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  variant; int /*<<< orphan*/  top; int /*<<< orphan*/  bottom; int /*<<< orphan*/  id; } ;
struct TYPE_15__ {int id; int /*<<< orphan*/  variant; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct TYPE_14__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; int /*<<< orphan*/  variant; int /*<<< orphan*/  id; } ;
struct TYPE_13__ {int /*<<< orphan*/  top; int /*<<< orphan*/  bottom; int /*<<< orphan*/  variant; int /*<<< orphan*/  id; } ;
struct TYPE_10__ {int id; int /*<<< orphan*/  variant; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct TYPE_9__ {int role; int id; int /*<<< orphan*/  top; int /*<<< orphan*/  bottom; int /*<<< orphan*/  variant; } ;
struct TYPE_11__ {int buildseq; TYPE_2__ version; TYPE_1__ compat; } ;
struct TYPE_12__ {int type; int len; TYPE_3__ info; } ;

/* Variables and functions */
 TYPE_8__ macid ; 
 TYPE_7__ nicid ; 
 int ns3info ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 TYPE_6__ priid ; 
 TYPE_5__ rfid ; 
 TYPE_4__* s3info ; 

__attribute__((used)) static int validate_identity(void)
{
	int i;
	int result = 1;
	int trump = 0;

	pr_debug("NIC ID: %#x v%d.%d.%d\n",
		 nicid.id, nicid.major, nicid.minor, nicid.variant);
	pr_debug("MFI ID: %#x v%d %d->%d\n",
		 rfid.id, rfid.variant, rfid.bottom, rfid.top);
	pr_debug("CFI ID: %#x v%d %d->%d\n",
		 macid.id, macid.variant, macid.bottom, macid.top);
	pr_debug("PRI ID: %#x v%d %d->%d\n",
		 priid.id, priid.variant, priid.bottom, priid.top);

	for (i = 0; i < ns3info; i++) {
		switch (s3info[i].type) {
		case 1:
			pr_debug("Version:  ID %#x %d.%d.%d\n",
				 s3info[i].info.version.id,
				 s3info[i].info.version.major,
				 s3info[i].info.version.minor,
				 s3info[i].info.version.variant);
			break;
		case 2:
			pr_debug("Compat: Role %#x Id %#x v%d %d->%d\n",
				 s3info[i].info.compat.role,
				 s3info[i].info.compat.id,
				 s3info[i].info.compat.variant,
				 s3info[i].info.compat.bottom,
				 s3info[i].info.compat.top);

			/* MAC compat range */
			if ((s3info[i].info.compat.role == 1) &&
			    (s3info[i].info.compat.id == 2)) {
				if (s3info[i].info.compat.variant !=
				    macid.variant) {
					result = 2;
				}
			}

			/* PRI compat range */
			if ((s3info[i].info.compat.role == 1) &&
			    (s3info[i].info.compat.id == 3)) {
				if ((s3info[i].info.compat.bottom >
				     priid.top) ||
				    (s3info[i].info.compat.top <
				     priid.bottom)) {
					result = 3;
				}
			}
			/* SEC compat range */
			if ((s3info[i].info.compat.role == 1) &&
			    (s3info[i].info.compat.id == 4)) {
				/* FIXME: isn't something missing here? */
			}

			break;
		case 3:
			pr_debug("Seq: %#x\n", s3info[i].info.buildseq);

			break;
		case 4:
			pr_debug("Platform:  ID %#x %d.%d.%d\n",
				 s3info[i].info.version.id,
				 s3info[i].info.version.major,
				 s3info[i].info.version.minor,
				 s3info[i].info.version.variant);

			if (nicid.id != s3info[i].info.version.id)
				continue;
			if (nicid.major != s3info[i].info.version.major)
				continue;
			if (nicid.minor != s3info[i].info.version.minor)
				continue;
			if ((nicid.variant != s3info[i].info.version.variant) &&
			    (nicid.id != 0x8008))
				continue;

			trump = 1;
			break;
		case 0x8001:
			pr_debug("name inforec len %d\n", s3info[i].len);

			break;
		default:
			pr_debug("Unknown inforec type %d\n", s3info[i].type);
		}
	}
	/* walk through */

	if (trump && (result != 2))
		result = 0;
	return result;
}