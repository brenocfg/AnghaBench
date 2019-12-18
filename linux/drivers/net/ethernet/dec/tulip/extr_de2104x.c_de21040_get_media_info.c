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
struct de_private {int media_type; int media_supported; int media_advertise; TYPE_1__* media; } ;
struct TYPE_2__ {unsigned int type; int /*<<< orphan*/  csr15; int /*<<< orphan*/  csr14; int /*<<< orphan*/  csr13; } ;

/* Variables and functions */
 unsigned int DE_MAX_MEDIA ; 
#define  DE_MEDIA_AUI 130 
 unsigned int DE_MEDIA_INVALID ; 
#define  DE_MEDIA_TP 129 
#define  DE_MEDIA_TP_FD 128 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_AUI ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/ * t21040_csr13 ; 
 int /*<<< orphan*/ * t21040_csr14 ; 
 int /*<<< orphan*/ * t21040_csr15 ; 

__attribute__((used)) static void de21040_get_media_info(struct de_private *de)
{
	unsigned int i;

	de->media_type = DE_MEDIA_TP;
	de->media_supported |= SUPPORTED_TP | SUPPORTED_10baseT_Full |
			       SUPPORTED_10baseT_Half | SUPPORTED_AUI;
	de->media_advertise = de->media_supported;

	for (i = 0; i < DE_MAX_MEDIA; i++) {
		switch (i) {
		case DE_MEDIA_AUI:
		case DE_MEDIA_TP:
		case DE_MEDIA_TP_FD:
			de->media[i].type = i;
			de->media[i].csr13 = t21040_csr13[i];
			de->media[i].csr14 = t21040_csr14[i];
			de->media[i].csr15 = t21040_csr15[i];
			break;
		default:
			de->media[i].type = DE_MEDIA_INVALID;
			break;
		}
	}
}