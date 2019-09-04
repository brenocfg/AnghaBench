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
struct hva_dev {unsigned int nb_of_encoders; int /*<<< orphan*/  nb_of_streamformats; int /*<<< orphan*/  streamformats; TYPE_1__** encoders; int /*<<< orphan*/  nb_of_pixelformats; int /*<<< orphan*/  pixelformats; } ;
struct TYPE_2__ {int /*<<< orphan*/  streamformat; int /*<<< orphan*/  pixelformat; } ;

/* Variables and functions */
 int /*<<< orphan*/  register_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void register_formats(struct hva_dev *hva)
{
	unsigned int i;

	for (i = 0; i < hva->nb_of_encoders; i++) {
		register_format(hva->encoders[i]->pixelformat,
				hva->pixelformats,
				&hva->nb_of_pixelformats);

		register_format(hva->encoders[i]->streamformat,
				hva->streamformats,
				&hva->nb_of_streamformats);
	}
}