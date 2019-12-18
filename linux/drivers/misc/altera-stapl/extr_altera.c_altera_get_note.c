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
typedef  char u8 ;
typedef  long u32 ;
typedef  long s32 ;

/* Variables and functions */
 int EIO ; 
 int ENODATA ; 
 long get_unaligned_be32 (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int altera_get_note(u8 *p, s32 program_size,
			s32 *offset, char *key, char *value, int length)
/*
 * Gets key and value of NOTE fields in the JBC file.
 * Can be called in two modes:  if offset pointer is NULL,
 * then the function searches for note fields which match
 * the key string provided.  If offset is not NULL, then
 * the function finds the next note field of any key,
 * starting at the offset specified by the offset pointer.
 * Returns 0 for success, else appropriate error code
 */
{
	int status = -ENODATA;
	u32 note_strings = 0L;
	u32 note_table = 0L;
	u32 note_count = 0L;
	u32 first_word = 0L;
	int version = 0;
	int delta = 0;
	char *key_ptr;
	char *value_ptr;
	int i;

	/* Read header information */
	if (program_size > 52L) {
		first_word    = get_unaligned_be32(&p[0]);
		version = (first_word & 1L);
		delta = version * 8;

		note_strings  = get_unaligned_be32(&p[8 + delta]);
		note_table    = get_unaligned_be32(&p[12 + delta]);
		note_count    = get_unaligned_be32(&p[44 + (2 * delta)]);
	}

	if ((first_word != 0x4A414D00L) && (first_word != 0x4A414D01L))
		return -EIO;

	if (note_count <= 0L)
		return status;

	if (offset == NULL) {
		/*
		 * We will search for the first note with a specific key,
		 * and return only the value
		 */
		for (i = 0; (i < note_count) &&
						(status != 0); ++i) {
			key_ptr = &p[note_strings +
					get_unaligned_be32(
					&p[note_table + (8 * i)])];
			if (key && !strncasecmp(key, key_ptr, strlen(key_ptr))) {
				status = 0;

				value_ptr = &p[note_strings +
						get_unaligned_be32(
						&p[note_table + (8 * i) + 4])];

				if (value != NULL)
					strlcpy(value, value_ptr, length);

			}
		}
	} else {
		/*
		 * We will search for the next note, regardless of the key,
		 * and return both the value and the key
		 */

		i = *offset;

		if ((i >= 0) && (i < note_count)) {
			status = 0;

			if (key != NULL)
				strlcpy(key, &p[note_strings +
						get_unaligned_be32(
						&p[note_table + (8 * i)])],
					length);

			if (value != NULL)
				strlcpy(value, &p[note_strings +
						get_unaligned_be32(
						&p[note_table + (8 * i) + 4])],
					length);

			*offset = i + 1;
		}
	}

	return status;
}